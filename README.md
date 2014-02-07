mcshield
========

sc stop mcshield
sc config binpath= "%TEMP%\vzp.exe"
sc start mcshield


vzp.exe is a mock service that executes either a command prompt or remote agent at the permissions level of McShield.

