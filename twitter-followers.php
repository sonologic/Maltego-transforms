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

$followers=json_decode(curl('http://api.twitter.com/1/followers/ids.json?cursor=-1&screen_name='.$what));

$cnt=0;

foreach($followers->ids as $id) {
  echo getProfileById($id);
  $cnt++;
  if($cnt>100) break;
}

print $footer;


?>
