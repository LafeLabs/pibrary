<?php

$dnaurl = "https://raw.githubusercontent.com/LafeLabs/pibrary/main/data/dna.txt";

if(isset($_GET["dna"])){
    $dnaurl = $_GET["dna"];
}


$baseurl = explode("data/",$dnaurl)[0];
$dnaraw = file_get_contents($dnaurl);
$dna = json_decode($dnaraw);

mkdir("data");
mkdir("php");
mkdir("scrolls");
mkdir("iconsymbols");

mkdir("imageset");
mkdir("symbolset");
mkdir("codelibrary");
mkdir("maplibrary");
mkdir("iconlibrary");

copy("https://raw.githubusercontent.com/LafeLabs/pibrary/main/php/replicator.txt","replicator.php");
copy("https://raw.githubusercontent.com/LafeLabs/pibrary/main/imageset/php/replicator.txt","imageset/replicator.php");
copy("https://raw.githubusercontent.com/LafeLabs/pibrary/main/symbolset/php/replicator.txt","symbolset/replicator.php");

copy("https://raw.githubusercontent.com/LafeLabs/pibrary/main/codelibrary/php/replicator.txt","codelibrary/replicator.php");
copy("https://raw.githubusercontent.com/LafeLabs/pibrary/main/maplibrary/php/replicator.txt","maplibrary/replicator.php");
copy("https://raw.githubusercontent.com/LafeLabs/pibrary/main/iconlibrary/php/replicator.txt","iconlibrary/replicator.php");



foreach($dna->html as $value){
    
    copy($baseurl.$value,$value);

}

foreach($dna->iconsymbols as $value){
    
    copy($baseurl."iconsymbols/".$value,"iconsymbols/".$value);

}

foreach($dna->data as $value){
    
    copy($baseurl."data/".$value,"data/".$value);
    
}

foreach($dna->php as $value){
 
    copy($baseurl."php/".$value,"php/".$value);
    copy($baseurl."php/".$value,explode(".",$value)[0].".php");

}

foreach($dna->scrolls as $value){
    
    if($value == "home"){
        copy($baseurl."scrolls/".$value,"scrolls/".$value);
    }

    
}


?>
<a href = "index.html">CLICK TO GO TO PAGE</a>
<style>
a{
    font-size:3em;
}
</style>
