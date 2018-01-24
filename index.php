<!DOCTYPE html>
<html>
<?php
//Include all necessary php files
include "php/common.inc";
include "php/results.inc";




?>
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <script type="text/javascript" src="js/javascript.js"></script>
</head>
<body>

  <?php
  // $results_data =  get_all_parks();
  ?>
	<!-- Header -->
  <script type="text/javascript">
        var map;
        var bounds;
    </script>
    <script
        src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAAwYiMKxsusdlIIJ5rcqcVTtr2ZYNQP4Q">
    </script>
	<?php include 'components/header.inc'; ?>
	<div id="body">

    <div id="homepage">

			<img src="images/homepage.jpg" alt="">
			<!-- center-content is a container for the content which appears on top of the homepage image -->
			<div id="center-content">
				<h2>Welcome</h2>
        <a href="search.php"><span>Search and review parks facilities in and around Brisbane, Australia.</span></a>
				

        <?php
        // display_map($results_data);
        ?>
		</div>
  </div>


    <?php include 'components/footer.inc'; ?>
</body>
</html>
