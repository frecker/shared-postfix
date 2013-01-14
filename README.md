shared-postfix
===

Abstract:

This projekt deals with the cryptosystem [1]. The code shows that a
brute force attack is possible without knowing the exact position of
the shared postfix of the passwords.


Installing:

"make" should compile the executables "create" und "bruteforce". The
library libssl is usually provided by openssl.


Usage:

"./create <password>" shows the md5sum of the password.

"./bruteforce <hint> <md5sum of the password>" tries to find the
password for the given md5sum.


Example:

We use "hjgf787j!gf0Lk" as the common postfix. Our first password uses
the prefix "eb3" and the second password uses "am5". First, we
calculate the md5sums:

./create 'eb3hjgf787j!gf0Lk' gives 940c6e7cc990d1fa241d77fadf18f79b

./create 'am5hjgf787j!gf0Lk' gives 96119cfc387bb3a917d6686a860db765

Now the attacker knows the first password and has the md5sum of the
second password.

./bruteforce 'eb3hjgf787j!gf0Lk' 96119cfc387bb3a917d6686a860db765

Depending on your hardware after some time you see

The password is am5hjgf787j!gf0Lk


Literature:

Ronald Eikenberg, "Sesam, öffne Dich nicht", c't 2/2011, p. 150-152
