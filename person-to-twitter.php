#!/usr/bin/env php
<?php

include_once('twitter.inc');

$what=$argv[1];

$header=<<<EOT
<MaltegoMessage> 
<MaltegoTransformResponseMessage>
<Entities>
EOT
;  
 
$footer=<<<EOT
</Entities>
</MaltegoTransformResponseMessage>
</MaltegoMessage>
EOT
;  
 
print $header;

        $output=curl('http://www.google.com/search?q="'.urlencode($what).'"+site%3Atwitter.com');

// color="green">http://twitter.com/FroYoShop -
        $num=preg_match_all('|color="green">http://twitter.com/([^\s</]+)[\s<]|',$output,$matches);

foreach ($matches[1] as $match) {
  echo profile($match); 
}

print $footer;


?>
