#skrypt wyswietla rozne kompunikaty w zaleznosci od dnia tygodnia

LC_TIME="C"
export LC_TIME
dzien=$(date +%a)
echo dzien = $dzien
#if [ $dzien = Sat ] || [ $dzien = Sun ] #to samo co niżej 
if test $dzien = Sat || test $dzien = Sun
then
  echo Weekend
else
  echo Dzien tygodnia
fi




