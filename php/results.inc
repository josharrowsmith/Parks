<?php
	// Function:  get_all_parks()
	// Description: a function to get all parks in the database
	// Input: none
	// Output: all parks
	function get_all_parks(){
		$query = 'SELECT * FROM parks';
		return perform_sql_query($query, null);
	}


	// Function: haversine($lat1, $lon1, $lat2, $lon2)
	// Description: implements the haversine equation to determine the distance between two points on the globe
	// Input: Two lat long values
	// Output: The distance, in km, between the two points
	// not my math found of stack overflow
	function haversine($lat1, $lon1, $lat2, $lon2){
		$lat1 = $lat1 * pi() / 180;
		$lon1 = $lon1 * pi() / 180;
		$lat2 = $lat2 * pi() / 180;
		$lon2 = $lon2 * pi() / 180;

		$q1 = cos($lon1 - $lon2);
		$q2 = cos($lat1 - $lat2);
		$q3 = cos($lat1 + $lat2);

		$rads = acos(0.5 * ((1.0 + $q1) * $q2 - (1.0 - $q1) * $q3));

		$distance = (3963.346 * $rads) * 1.60934;
		return $distance;
	}

	// Function:  get_parks_by_location($lat, $long, $distance)
	// Description: a function to get all parks by location
	// Input: users latitude and longitude as well as the maximum distance
	// Output: all parks within the maximum distance
	function get_parks_by_location($lat, $long, $distance){
		$all_parks = get_all_parks()->fetchAll();
		$matching_parks = array();
		foreach ($all_parks as  $park){
			if(haversine(floatval($park['latitude']), floatval($park['longitude']), $lat, $long) < $distance){
				$matching_parks[] = $park;
			}
		}
		return $matching_parks;
	}

	// Function:  get_parks_by_rating($min)
	// Description: a function to get all parks by rating
	// Input: minimum allowable rating
	// Output: all parks with a rating greater than the minimum rating
	function get_parks_by_rating($min){
		$query = "SELECT * FROM parks WHERE rating > $min";

		return perform_sql_query($query, null);
	}

	// Function:  get_parks_by_search($text)
	// Description: a function to get all parks by a keyword(s)
	// Input: the keyword(s)
	// Output: all parks matching the keyword(s)
	function get_parks_by_search($text){
		$lower_string = strtolower($text);
		$query = "SELECT * FROM parks WHERE parkid IN (SELECT parkID from reviews WHERE LOWER(message) LIKE \"%".$lower_string."%\") OR LOWER(name) LIKE \"%".$lower_string."%\"";

		return perform_sql_query($query, null);
	}



	// Function:  get_parks_by_suburb($suburb)
	// Description: a function to get all parks by a suburb
	// Input: the suburb
	// Output: all parks matching the suburb
	function get_parks_by_suburb($suburb){
		$lower_string = strtolower($suburb);
		$query = "SELECT * FROM parks WHERE LOWER(suburb) = \"".$lower_string."\"";

		return perform_sql_query($query, null);
	}

	// Function:  get_search_results(){
	// Description: a complex function to get search results based on the set GET request parameters
	// Input: none
	// Output: all parks matching the search parameters
	function    get_search_results(){

		if(empty($_GET)){
			// if the search has no parameters then return all parks
			return get_all_parks();
		}


		if(!isset($_GET['distance']) || $_GET['distance'] == ""){
			// If the distance is not set then set it to 10km
			$distance = 10;
		} else {
			// Else set it to the required distance
			$distance = htmlspecialchars($_GET['distance'], ENT_QUOTES, 'UTF-8');
		}

		// loop through each field of the GET request
		foreach($_GET as $field => $value){
			$value = htmlspecialchars($value, ENT_QUOTES, 'UTF-8');

			// If the value is not empty and is not the distance parameter
			if ($value != "" & $value != "distance"){

				// If the set field is lat and lon is not empty
				if ($field == 'lat' && $_GET['lon'] != ""){
					// Then get parks by distance
					$lon = htmlspecialchars($_GET['lon'], ENT_QUOTES, 'UTF-8');
					$result = get_parks_by_location($value, $lon, $distance);
					break;
				}

				// If the set field is lon and lat is not empty
				else if ($field == 'lon' && $_GET['lat'] != ""){
					// Then get parks by distance
					$lat = htmlspecialchars($_GET['lat'], ENT_QUOTES, 'UTF-8');
					$result = get_parks_by_location($lat, $value, $distance);
					break;
				}

				// If the set field is rating
				else if ($field == 'rating') {
					$result = get_parks_by_rating($value);
					break;
				}

				// If the set field is keyword search
				else if ($field == 'search'){
					$result = get_parks_by_search($value);
					break;
				}


				// If the set field is suburb
				else if ($field == 'suburb'){
					$result = get_parks_by_suburb($value);
					break;
				}
			}

			// if the code reaches this point (none of the above conditions are met)
			if (!isset($result)){
				// Then get all parks
				$result = get_all_parks();
			}

		}

		// If any of the above searches return no results
		if((is_array($result) & count($result) < 1) || (!is_array($result) && $result->rowCount() < 1)){
			// then set an error message and return to the search page
			$_SESSION['errorMessage'] = 'No parks matched your search';
			header("Location: ".get_base_url()."/search.php?".$field."=".$value);
			exit();
		}

		return $result;
	}


	// Function:  display_results_table($results_data)
	// Description: a function to display the search results in a tabular format
	// Input: the search results
	// Output: none
	function display_results_table($results_data){
		// Start the table and set all of the headings
		echo '<table id="results">'.
			'<tr>'.
				'<th>Name</th>'.
				'<th>Location</th>'.
			'</tr>';

		// For each park in the search results , add a table row
		foreach($results_data as $park){
			echo "<tr>";
			echo "<td ><a class='park_title' href=\"park.php?id=".$park['parkid']."\">".$park['name']."</a></td>";
			echo "<td><a href=\"park.php?id=".$park['parkid']."\">".$park['suburb'].", ".$park['street']."</a></td>";
			echo "</tr>";
		}

		// Close the table
		echo '</table>';
	}
?>
