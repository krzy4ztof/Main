touch README.txt
git init
git add README.txt
git commit -m "first commit"
git remote add origin https://github.com/krzy4ztof/Main.git
git push -u origin master

svnvars.bat
svn co https://krzysztof-pc/svn/svn/MapEditor/trunk/ MapEditorTrunk

git co https://github.com/krzy4ztof/Main

***************************
***	Nowe repozytorium	***
***************************

zalozyc nowy katalog NewRepo
cd NewRepo
git init
git remote add origin https://github.com/krzy4ztof/Main.git
git co https://github.com/krzy4ztof/Main

***************************************************************
***	Pobranie do repozytorium zmian z remote repozytorium	***
***************************************************************
git pull

***********************************************
***	Wyslanie zmian do remote repozytorium	***
***********************************************
#Dodanie wszystkich plikow do commit
git add *
git commit *
git push -u origin master

***************************************
***	Rozna wielkosc liter w Windows	***
***************************************
.git/config
#ignorowanie wielkosci znakow - domyslnie dla Windows
#ignorecase = true
#uwzglednianei wielkosci znakow - Linux
ignorecase = false



