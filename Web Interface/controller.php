<?php

require_once("classes/phpMQTT.php");

$slider_name = $_REQUEST['slider_name'];
$slider_value =  $_REQUEST['slider_value'];

$pre_topic = "test/";
$host = "mqtt.domain.com";  /// Update to your server 
$port = 1883;
$username = NULL; 
$password = NULL; 
$message = "";
$clientID = "ClientID".rand();

if($slider_name != ""){

        $slider_name = $pre_topic.$slider_name;
        $mqtt = new phpMQTT($host, $port, $clientID); 
        if (!$mqtt->connect(true,NULL,$username,$password)) {
                echo "Failed to connect or timed out";
                die();
        }

        $mqtt->publish($slider_name,$slider_value,0,0); //topic,message,qos,retain
        $mqtt->close();

}else{

        $done = 0;
        $mqtt = new phpMQTT($host, $port, $clientID);
        if(!$mqtt->connect()){
                exit(1);
        }

        $topics[$pre_topic."json"] = array("qos"=>0, "function"=>"procmsg");
        $mqtt->subscribe($topics,0);
        $start_time = time();

        while (!$done && !hasTimedout() && $mqtt->proc()) {

        }

        $mqtt->close();
}


function procmsg($topic,$msg) {
        global $done;
        $done = 1;
        echo $msg;
}

function hasTimedout() {
        global $start_time;
        return (time() - $start_time > 5);//waits up to 10 sec
        }


die();    
?>