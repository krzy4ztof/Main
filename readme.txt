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
git clone https://github.com/krzy4ztof/Main

***************************************************************
***	Pobranie do repozytorium zmian z remote repozytorium	***
***************************************************************
git pull

****************************************************************
***	Założenie nowego repozytorium oraz						****
***	Pobranie do repozytorium zmian z remote repozytorium	****
****************************************************************
git init
git pull https://github.com/swarmsim/swarm.git
git remote add origin https://github.com/swarmsim/swarm.git

***********************************************
***	Wyslanie zmian do remote repozytorium	***
***********************************************
#Dodanie wszystkich plikow do commit
git add *
git commit -m ''

git push -u origin master 
lub 
git push

***************************************
***	Rozna wielkosc liter w Windows	***
***************************************
.git/config
#ignorowanie wielkosci znakow - domyslnie dla Windows
#ignorecase = true
#uwzglednianei wielkosci znakow - Linux
ignorecase = false

***********************************************
***	GitHub Desktop							***
***	Wyslanie zmian do remote repozytorium	***
***********************************************
Panel -> Changes

Commit to master.
Title, Description


