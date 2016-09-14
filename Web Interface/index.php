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
    <h1>Marisa's Room</h1>
  </div>

  <div data-role="main" class="ui-content">
    <form method="post" action="">
    
                <h2>Lamp Control</h2> 
                
        <label for="flip-mini">Lamp Control</label>
                <select name="auto_outlet" id="autoOutlet1" class="control_element" data-role="slider" data-mini="true">
                  <option value="0">Off</option>
                  <option value="1">On</option>
                </select>


                <h2>Star Light Control</h2>    

        <label for="flip-mini">Star Lights:</label>
                <select name="star_light" id="starLights" class="control_element" data-role="slider" data-mini="true">
                  <option value="0">Off</option>
                  <option value="1">On</option>
                </select>
      
                <h2>Night Light Control</h2>

        <label for="flip-mini">Night Light:</label>
                <select name="night_light" id="nightLight" class="control_element" data-role="slider" data-mini="true">
                  <option value="0">Off</option>
                  <option value="1">On</option>
                </select>
      

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