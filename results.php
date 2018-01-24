<!DOCTYPE html>
<html>
<?php
// Include all necessary php files
include "php/common.inc";
include "php/results.inc";
include "php/search.inc";

// Start the users session
session_start();


// Get the results for the search
$results_data = get_search_results();
if (!is_array($results_data)){
    $results_data = $results_data -> fetchAll();



}
?>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <script type="text/javascript" src="js/javascript.js">
		// These variables are global variables used for the map
        var map;
        var bounds;
    </script>
    <script src="https://maps.googleapis.com/maps/api/js?key="></script>
</head>
<body>
	<!-- Header -->
	<?php include 'components/header.inc'; ?>
	<!-- Body -->
	<div id="body">
    <br>
		<p id="title">Results</p>
		<!-- if there is an error message, display it -->
		<?php display_error_message();?>
		<!-- display the map with search results added as markers -->
		<?php display_map($results_data);?>
		<!-- display search results in a table -->
		<?php display_results_table($results_data)?>
    <br>
	</div>
	<!-- Footer -->
	<?php include 'components/footer.inc'; ?>
</body>
</html>
