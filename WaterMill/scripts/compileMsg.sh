#!/bin/sh

#1. Otworzyć konsolę MinGW
#2. cd /c/Users/Krzysztof/home/myImportantFiles/projects/git/Main/WaterMill/assets/pl/LC_MESSAGES
#3. msgfmt --output-file=watermill.mo watermill.po
#4. Zostanie wygenerowany plik watermill.mo

en_dir=../assets/strings/en/lc_messages/
pl_dir=../assets/strings/pl/lc_messages/

msgfmt --output-file=${en_dir}watermill.mo ${en_dir}watermill.po
msgfmt --output-file=${pl_dir}watermill.mo ${pl_dir}watermill.po
