
(sleep 1
echo "helo whitehouse.gov"
echo "mail from: "$1
echo "rcpt to: "$2
echo "data"
echo "Subject: This is spam!"
echo $3
echo "."
sleep 1
) | telnet mail.cs.ucr.edu 25 
