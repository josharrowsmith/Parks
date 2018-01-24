<!DOCTYPE html>
<html>
<?php
// Include all necessary php files
include "php/common.inc";
include "php/park.inc";
include 'components/header.inc';
Include 'db.php';

// Start the users session
// session_start();


// Get all park data
$park_data = get_park_by_id($_GET['id'])->fetchAll();

// Get all reviews data
// $reviews_data = get_reviews_by_id($_GET['id']);
?>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="css/style.css">
	<script src="js/javascript.js"></script>
<!--	These variables are global variables used for the map-->
	<script type="text/javascript">
        var map;
        var bounds;
    </script>
    <script
        src="https://maps.googleapis.com/maps/api/js?key=">
    </script>
</head>
<body>
	<div id="body">
    <br>
		<!-- Header -->
		<?php

		display_map($park_data);
		?>

				<?php
        echo "<h2>","Name :  ",$park_data[0]['name'],"<br>",
        "Street :  ", $park_data[0]['street'],"<br>",
        "Suburb :  ",$park_data[0]['suburb'],"<br>",
        "Rating :  ",$park_data[0]['rating'];
        ?>
    <?php
    if( isset($_SESSION['logged_in']) ){
        	//checking if login
          ?>
          <form method="post">
            <span>Make a review</span>
            <select name="rating" id="rating">
              <option value="">Select a rating</option>
              <option value="1">1 Star</option>
              <option value="2">2 Stars</option>
              <option value="3">3 Stars</option>
              <option value="4">4 Stars</option>
              <option value="5">5 Stars</option>
            </select>
            <input type="submit" class="submit" name="review" id="review" value="Add Review"/>
          </form>
        </div>
        <?php



          if (isset($_POST['review'])){
          }
        }

        ?>
	<!-- Footer -->
	<?php include 'components/footer.inc'; ?>
</body>
</html>
