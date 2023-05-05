# skrypt znajduje wszystkie pliki o podanym rozszerzeniu

rozszerzenie=$1
N=$2
archiwum=$3

tar -cf $archiwum.tar $(find ./ -name "*.$rozszerzenie" -mtime -$N -readable)
