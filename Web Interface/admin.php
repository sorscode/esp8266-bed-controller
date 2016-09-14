<!DOCTYPE xhtml>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css">
<script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
<script src="http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>

<script type="text/javascript">
        $(function() {

                $.ajax({
            type: "GET",                    
                        url: "controller.php",
            cache: false,
            data: { slider_name: "", slider_value: ""},
            success: function(data) {                       
                                var dataObj = $.parseJSON(data);
                                $.each( dataObj, function( key, value ) {  
                                        if(key != "version"){
                                                $("#"+key).val(value).slider("refresh");
                                        }  
                                });
                },
            error: function(data) {
                                alert(data.responseText);
                        }
        }); 
                
                $( ".control_element" ).on( 'slidestop', function( event ) { 
                        var slider_name = $(this).attr("id");
                        var slider_value = $(this).slider().val();  
  
                        $.ajax({
                    type: "GET",                    
                                url: "controller.php",
                    cache: false,
                    data: {slider_name: slider_name, slider_value: slider_value},
                    success: function(data) {                                                 
                                        //alert(data);
                        },
                    error: function(data) {
                                        alert("Error: " + data);
                                }
                }); 
                });

                $( ".control_element_button" ).on( 'click', function( event ) { 
                        var slider_name = $(this).attr("id");
                        var slider_value = $(this).val();  
  
                        $.ajax({
                    type: "GET",                    
                                url: "controller.php",
                    cache: false,
                    data: {slider_name: slider_name, slider_value: slider_value},
                    success: function(data) {                                                 
                                        //alert(data);
                        },
                    error: function(data) {
                                        alert("Error: " + data);
                                }
                }); 
                });

        });

</script>

<style type="text/css">
        .ui-overlay-a, .ui-page-theme-a, .ui-page-theme-a .ui-panel-wrapper {color:#fff !important; text-shadow: 0 1px 0 #000;}
        h2 {color:#fff !important; border-bottom:1px solid #ccc;}        
        .ui-content {
            background: url(img/dory.jpg);
            background-repeat:no-repeat;
            background-position:center center;
            background-size:cover; 
            max-height:100%; 
        }
        .customButton {
        width: 5.8em !important;
                }
</style>
</head>
<body>

<div data-role="page">
  <div data-role="header">
    <h1>Marisa's Room - Admin Page</h1>
  </div>

  <div data-role="main" class="ui-content">
    <form method="post" action="">
    

                <h2>LED Controls</h2>    

                <label for="led_channel1">LED Channel 1:</label>
        <input type="range" name="test_channel1" id="ledChannel1" class="control_element" value="0" min="0" max="1023">
      
        <label for="led_channel2">LED Channel 2:</label>
        <input type="range" name="test_channel2" id="ledChannel2" class="control_element" value="0" min="0" max="1023">
      
        <label for="led_channel3">LED Channel 3:</label>
        <input type="range" name="test_channel3" id="ledChannel3" class="control_element" value="0" min="0" max="1023">
      
        <label for="led_channel4">LED Channel 4:</label>
        <input type="range" name="test_channel4" id="ledChannel4" class="control_element" value="0" min="0" max="1023">
      

                <h2>Outlet Controls</h2> 
  
        <label for="flip-mini">Outlet 1:</label>
                <select name="outlet_channel1" id="outlet1" class="control_element" data-role="slider" data-mini="true">
                  <option value="0">Off</option>
                  <option value="1">On</option>
                </select>

                <label for="flip-mini">Outlet 2:</label>
                <select name="outlet_channel2" id="outlet2" class="control_element" data-role="slider" data-mini="true">
                  <option value="0">Off</option>
                  <option value="1">On</option>
                </select>

                <h2></h2>
                <div class="ui-btn ui-input-btn ui-shadow customButton">
                  Update
                  <input type="button" data-corners="false" data-enhanced="true" value="1" id="update" class="control_element_button"></input>
                </div>

                <p>&nbsp;</p>
                <p>&nbsp;</p>
                <p>&nbsp;</p>
                <p>&nbsp;</p>
                <p>&nbsp;</p>
                <p>&nbsp;</p>
                <p>&nbsp;</p>

    </form>
  </div>
</div>
</body>
</html>