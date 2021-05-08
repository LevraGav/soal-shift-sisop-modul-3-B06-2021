#!bin/bash

#Cari semua line error dan count berapa kali keluar
perm="$(grep -o "Permission denied while closing ticket" syslog.log | wc -l)"
notexist="$(grep -o "Ticket doesn't exist" syslog.log | wc -l)"
failedcon="$(grep -o "Connection to DB failed" syslog.log | wc -l)"
modify="$(grep -o "The ticket was modified while updating" syslog.log | wc -l)"
close="$(grep -o "Tried to add information to closed ticket" syslog.log | wc -l)"
timeout="$(grep -o "Timeout while retrieving information" syslog.log | wc -l)"

#print error tersebut dan sort kolom 2 dengan menggunakan fungsi sort dan menggunakan , sebagai delimiter lalu sed Error, Count di line 1
printf "Permission denied while closing ticket,%d\n
Ticket doesn't exist,%d\n
The ticket was modified while updating,%d\n
Connection to DB failed,%d\n
Tried to add information to closed ticket,%d\n
Timeout while retrieving information,%d\n" $perm $notexist $modify $failedcon $close $timeout | sort -t, -k2 -nr | sed '1 i\Error,Count' > error_message.csv

#Potong semua ��W�FV