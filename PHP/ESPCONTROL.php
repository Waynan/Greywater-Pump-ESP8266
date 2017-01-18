<?php


$light = $_GET['light'];
if($light == "on") {
  $jsonString = file_get_contents('light.json');
  $data = json_decode($jsonString, true);
  $data['light'] = "on";
  $newJsonString = json_encode($data);
  file_put_contents('light.json', $newJsonString);
  } 
else if ($light == "off") {
  $jsonString = file_get_contents('light.json');
  $data = json_decode($jsonString, true);
  $data['light'] = "off";
  $newJsonString = json_encode($data);
  file_put_contents('light.json', $newJsonString);
}
?>

<html>
  <head>      
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    
    <title>ESP8266</title>
   
</html>
