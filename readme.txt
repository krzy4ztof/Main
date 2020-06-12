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
***	Znaki końca linii	***
***************************
Rozwiązanie problemu naprzemiennych commitów z Windows i Linuxa i różnych znaków końca linii w obu systemach.

git config --global core.autocrlf true

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

*******************************************************
***	Wyslanie zmian do remote repozytorium Ubuntu	***
*******************************************************

Command line:

git add *
git commit -m 'commit name'
git push

Username for 'https://github.com': krzy4ztof@poczta.onet.pl
Password for 'https://krzy4ztof@poczta.onet.pl@github.com': 

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


***********************************
***	Konfiguracja Kdiff3 Ubuntu	***
***********************************

Configure gedit as editor for git purposes (for example editing comments).
	git config --global core.editor gedit
	
Configure KDiff3 as differences viewer and merging editor.
	git config --global diff.tool kdiff3
	git config --global merge.tool kdiff3


-----	-----	-----	------	------

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

git commit -m 'Tile for commit'
git push

***************
***	Rename	***
***************
Rename from Windows64Calls.hpp to Windows64Calls.h

git mv Windows64Calls.hpp Windows64Calls.h


*******************
***	Conflicts	***
*******************
Solve conflicts

git mergetool


*******************
***	Git Push	***
*******************
git config --global push.default simple

[push]
	default = simple
	


***************
***	SSH KEY	***
***************

https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/

cd ~
ls -al ~/.ssh

ssh-keygen -t rsa -b 4096 -C "mine@mail"

Enter passphrase (empty for no passphrase): [empty]
Enter same passphrase again: [empty]

/c/Users/Krzysztof/.ssh/
	id_rsa
	id_rsa.pub

eval $(ssh-agent -s)

ssh-add ~/.ssh/id_rsa
	 _rsa.pub

https://github.build.ge.com/settings/profile
SSH and GPG keys -> New SSH Key

Paste from clipboard into Key field.

***********************	
***	pull requests	***
***********************

git checkout -b dev	

git commit -m 'unit tests makefiles'

git push
git push --set-upstream origin dev


git checkout master
git pull

git checkout dev
git merge master
git stash apply

(dev)
git fetch --all
git rebase origin/master



