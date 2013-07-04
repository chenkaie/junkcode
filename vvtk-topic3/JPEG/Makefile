# batch make file for apps

JPEG_APP = jpegapp
JPEG_LIB = jpeglib
BIN      = bin
SAMPLES  = samples
#$(error $(JPEG_APP))
#$(warning $(JPEG_APP))

all :
	@echo "==> Build jpeglib =========================="
	for i in $(JPEG_LIB); do \
		(cd $$i; make all) \
	done
	@echo "==> Build jpegapp =========================="
	for i in $(JPEG_APP); do \
		(cd $$i; make all) \
	done

install :
	@echo "==> Install app & jpeg file================="
	cp $(JPEG_APP)/jpegapp $(BIN)
	cp $(SAMPLES)/sample.jpg $(BIN)
	cp $(SAMPLES)/sample.gif $(BIN)


clean :
	for i in $(JPEG_LIB); do \
		(cd $$i; make clean) \
	done
	for i in $(JPEG_APP); do \
		(cd $$i; make clean) \
	done
	rm -f $(BIN)/jpegapp $(BIN)/jpg-sof0.JPG
	@echo "==> Clean Successfully ===================="

.PHONY:all clean jpeglib install
