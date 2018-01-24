<?php

	// Function: get_base_url()
	// Description: Returns the base url of the website
	// Input: none
	// Output: Base url of website
	function get_base_url(){
		return "127.0.0.1/{$_Server['HTTP_HOST']}";
	}


	function get_sql_connector(){
		$pdo = new PDO('mysql:host=localhost;dbname=dbname','admin', 'secret');
		$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		return $pdo;

	}

	// Function: perform_sql_query($query, $parameters)
	// Description: A single function to perform sql queries
	// Input: the sql query string and an array containing
	// all the parameters to be bound to the query
	// Output: The result object of the query else
	// redirects to error page if error has occurred
	//found this of a webiste
	function perform_sql_query($query, $parameters){
		// Get the sql connector object
		$pdo = get_sql_connector();

		try {
			// prepare the query
			$result = $pdo->prepare($query);

			// check if the parameters is not null
			if(!is_null($parameters)){
				// Loop over each parameter and bind to query
				while($value = current($parameters)){
					$result->bindValue(':'.key($parameters), $value);
					next($parameters);
				}
			}

			// Execute the query
			$result->execute();

			// Return the result
			return $result;
		} catch (PDOException $e) {
			// Set a useful error message
			//$_SESSION['errorMessage'] = $result->queryString."<br><br>".json_encode($parameters)."<br><br>".$e->getMessage();
			$_SESSION['errorMessage'] = $e->getMessage();

			// Redirect to error page
			header("Location: ".get_base_url()."/error.php");
			exit();
		}
	}

	// Function: display_map($search_data)
	// Description: a single function to display a map
	// with each park added as a marker
	// error messages from the users session
	// Input: the search data from the parks table
	// Output: none
	function display_map($search_data){

		// Set up and init an empty map
		echo '<div class="googleMap" id="googleMap"></div>';
		echo '<script>initMap();</script>';

		// Add each park as a marker on the map
		foreach($search_data as $park){
			echo '<script>addMarkerToMap('.$park['latitude'].','.$park['longitude'].
				',"'.$park['name'].'","park.php?id='.$park['parkid'].
				'","'.$park['rating'].'","'.$park['suburb'].
				'","'.$park['street'].'");</script>';
		}
	}

?>
