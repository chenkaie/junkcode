#!/bin/sh
change_codec()
{
	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_codectype=h264"
	sleep 10
	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_codectype=mpeg4"
	sleep 10
	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_codectype=mjpeg"
	sleep 10
}

while true
do
	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_resolution=1920x1080"
	sleep 10
	change_codec

	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_resolution=176x144"
	sleep 10
	change_codec

	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_resolution=1600x904"
	sleep 10
	change_codec

	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_resolution=384x216"
	sleep 10
	change_codec

	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_resolution=1360x768"
	sleep 10
	change_codec

	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_resolution=640x360"
	sleep 10
	change_codec

	curl --user root:si1 --url "http://172.16.83.62/cgi-bin/admin/setparam.cgi?videoin_c0_s0_resolution=1280x720"
	sleep 10
done
