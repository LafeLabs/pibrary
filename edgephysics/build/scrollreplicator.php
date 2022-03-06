<pre>
<?php

$sourceurl = file_get_contents("data/sourceurl.txt");

//if there is no / add one, but keep it if it already exists

copy($sourceurl."/data/scroll.txt","data/scroll.txt");

//add "data/scroll.txt" to the source url
//copy the scroll to data/scroll.txt


echo($sourceurl."/data/scroll.txt");

?>
</pre>
<a href = "magic.html">MAGIC</a>
<style>
body{
    background-color:black;
    color:#00ff00;
}
a{
    font-size:5em;
    color:#ff2cb4;
    font-family:courier;
}
</style>
