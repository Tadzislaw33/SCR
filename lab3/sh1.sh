while:
do
	echo "sh1 working"
	ls > FIFO
	cat zadanie.txt < FIFO
	sleep 1
done

