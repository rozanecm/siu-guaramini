printf "deleting old *.o files\n"
find . -maxdepth 1 -type f -iname \*.o -delete
echo make
make -f Makefile_client_server
printf "updating test directories\n"
bash updateExes.sh
