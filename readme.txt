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

Push to the remote.
Icon -> Sync icon - "Pull changes from and push local changes on master to the remote"

*******************************
***	Konfiguracja WinMerge	***
*******************************

W pliku
C:\Users\User\.gitconfig 
dodać 

-----	-----	-----	------	------
[mergetool]
	prompt = false
    keepBackup = false
    keepTemporaries = false

[merge]
    tool = winmerge

[mergetool "winmerge"]
    name = WinMerge
	trustExitCode = true
    cmd = "/c/Program\\ Files\\ \\(x86\\)/WinMerge/WinMergeU.exe" -u -e -dl \"Local\" -dr \"Remote\" $LOCAL $REMOTE $MERGED

[diff]
    tool = winmerge

[difftool "winmerge"]
    name = WinMerge
    trustExitCode = true
	#    cmd = "/c/Program\\ Files\\ \\(x86\\)/WinMerge/WinMergeU.exe" -e -u $LOCAL $REMOTE
	cmd = "/c/Program\\ Files\\ \\(x86\\)/WinMerge/WinMergeU.exe" -e -ub -x -wl -u -maximise -dl "base" \"$LOCAL\" \"$REMOTE\"

[core]
	autocrlf = false
	
-----	-----	-----	------	------

Winmerge konfiguracja:
Menu -> Edit -> Options 
Compare -> General
	Whitespace -> Ignore all
	Ignore carriage return differences (Windows/Linux/Mac)
	
	
Użycie:

git difftool
git difftool HEAD
git diftool --cached

***************
***	Remove	***
***************
Remove a file from a Git repository without deleting it from the local filesystem

cd  /c/home/myImportantFiles/projects/git/Main/WaterMill/settings/codeblocks/Watermill
git add *
git rm --cached Watermill.depend
git rm --cached Watermill.exe.stackdump
git rm --cached Watermill.layout

