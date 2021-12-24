
## [HOME](scrolls/home)

# Cybermagic


 We use the term "magic" here to mean sets of things which include the *desire* to replicate the set.  Cybermagic is sets of files on a computer system which include scripts to replicate the whole set as well as both documents on *how* to replicate the set and also on *why* we want to replicate it.  

Every single piece of information we store on any computer ever in our system must be part of this.  Whether it's saving files to a server, collecting data from an environmental sensor, programming a robot for industrial automation, putting up a useful web application or calculating physical quantities, *all* these programs are part of our system of self-replication.  

We also specify that all programs must be able to replicate from within a web browser.  Once the basic system is installed on any given machine, it is possible to replicate, edit and delete all files on the system from the browser. This includes all the replicator, editor, and deletor files themselves.  

There are five basic languages we use for this, which we loosely connect with the archetypes of the five elements of alchemy.  These are:

*HTML*.  HTML is short for Hyper Text Markup Language.  


 Cyber magic is self-replicating digital media.  This is an *example* of organic media.  We replicate, fork, edit, destroy, replicate and edit again, and fork again and again.  

 - what is magic.
 - set magic.
 - five elements of code
 - all the other languages: python, arduino, javascript, latex, markdown, JSON, HTML, CSS, PHP
 - editor.php
 - replicator.php
 - latex work flow, pandoc, pdf, etc
 - structure of PHP scripts
 - set replicator
 - scroll set replicator
 - file set replicator
 - code set replicator
 - delete file
 - recursive delete
 - nuke it all from orbit and start again
 - github work flow
 - building new apps and replicating them, editing the replicator
 - getting the system working on other platforms
 - cybermagic apps
 - web calculators

## Replication on Github

Part of the replication of the Pibrary system involves replicating and forking the code.  To fork all the code in a Cybermagic code set, start a new Github Repository with a CC0 PUBLIC DOMAIN license, and clone it to your computer.  Get PHP working from the command line on that computer.  It is already installed on a Mac.  On PC install Ubuntu under Windows and then install PHP.  Create a new file in the new directory called replicator.php and copy the code in [php/replicator.txt](php/replicator.txt) into it.  Then run from the command line:

```
php replicator.php
```

Now all the code is copied and you can push the whole thing to your github repository, which you can call pibrary if you want, or immediately fork to something new. 

To run the local PHP server, you can type from the command line

```
sudo php -S localhost:80
```
Then point any web browser to [http://localhost/](http://localhost/).  Now you can edit all the code using [editor.php](editor.php) and read about how to work with the code system in [the cybermagic scroll](scrolls/cybermagic).

To make things easier edit the file in `~/.bashrc` to include the line:

```
alias s = 'sudo php -S localhost:80'
```
as well as the line to change into the directory you're working in automatically with `cd`.



