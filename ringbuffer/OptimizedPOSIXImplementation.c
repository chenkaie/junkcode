#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

#define report_exceptional_condition() abort ()

struct ring_buffer
{
	void *address;

	unsigned long count_bytes;
	unsigned long write_offset_bytes;
	unsigned long read_offset_bytes;
};

//Warning order should be at least 12 for Linux
void
ring_buffer_create (struct ring_buffer *buffer, unsigned long order)
{
	char path[] = "/dev/shm/ring-buffer-XXXXXX";
	int file_descriptor;
	void *address;
	int status;

	file_descriptor = mkstemp (path);
	if (file_descriptor < 0)
		report_exceptional_condition ();

	status = unlink (path);
	if (status)
		report_exceptional_condition ();

	buffer->count_bytes = 1UL << order;
	buffer->write_offset_bytes = 0;
	buffer->read_offset_bytes = 0;

	status = ftruncate (file_descriptor, buffer->count_bytes);
	if (status)
		report_exceptional_condition ();

	buffer->address = mmap (NULL, buffer->count_bytes << 1, PROT_NONE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (buffer->address == MAP_FAILED)
		report_exceptional_condition ();

	address =
		mmap (buffer->address, buffer->count_bytes, PROT_READ | PROT_WRITE,
				MAP_FIXED | MAP_SHARED, file_descriptor, 0);

	if (address != buffer->address)
		report_exceptional_condition ();

	address = mmap (buffer->address + buffer->count_bytes,
			buffer->count_bytes, PROT_READ | PROT_WRITE,
			MAP_FIXED | MAP_SHARED, file_descriptor, 0);

	if (address != buffer->address + buffer->count_bytes)
		report_exceptional_condition ();

	status = close (file_descriptor);
	if (status)
		report_exceptional_condition ();
}

void
ring_buffer_free (struct ring_buffer *buffer)
{
	int status;

	status = munmap (buffer->address, buffer->count_bytes << 1);
	if (status)
		report_exceptional_condition ();
}

void *
ring_buffer_write_address (struct ring_buffer *buffer)
{
	/*** void pointer arithmetic is a constraint violation. ***/
	return buffer->address + buffer->write_offset_bytes;
}

void
ring_buffer_write_advance (struct ring_buffer *buffer,
		unsigned long count_bytes)
{
	buffer->write_offset_bytes += count_bytes;
}

void *
ring_buffer_read_address (struct ring_buffer *buffer)
{
	return buffer->address + buffer->read_offset_bytes;
}

void
ring_buffer_read_advance (struct ring_buffer *buffer,
		unsigned long count_bytes)
{
	buffer->read_offset_bytes += count_bytes;

	if (buffer->read_offset_bytes >= buffer->count_bytes)
	{
		buffer->read_offset_bytes -= buffer->count_bytes;
		buffer->write_offset_bytes -= buffer->count_bytes;
	}
}

unsigned long
ring_buffer_count_bytes (struct ring_buffer *buffer)
{
	return buffer->write_offset_bytes - buffer->read_offset_bytes;
}

unsigned long
ring_buffer_count_free_bytes (struct ring_buffer *buffer)
{
	return buffer->count_bytes - ring_buffer_count_bytes (buffer);
}

void
ring_buffer_clear (struct ring_buffer *buffer)
{
	buffer->write_offset_bytes = 0;
	buffer->read_offset_bytes = 0;
}

int main(int argc, const char *argv[])
{
	struct ring_buffer buf;
	ring_buffer_create (&buf, 12);
	
	return 0;
}

/*Note, that initial anonymous mmap() can be avoided - after initial mmap() for descriptor fd,
  you can try mmap() with hinted address as (buffer->address + buffer->count_bytes) and if it fails -
  another one with hinted address as (buffer->address - buffer->count_bytes).
  Make sure MAP_FIXED is not used in such case, as under certain situations it could end with segfault.
  The advantage of such approach is, that it avoids requirement to map twice the amount you need initially
  (especially useful e.g. if you want to use hugetlbfs and the allowed amount is limited)
  and in context of gcc/glibc - you can avoid certain feature macros
  (MAP_ANONYMOUS usually requires one of: _BSD_SOURCE, _SVID_SOURCE or _GNU_SOURCE).*/
