<?php

	// Function: add_suburb_options($preset)
	// Description: A function to populate the suburbs option field
	// Input: The value of the previously selected suburb 
	// Output: none
	function add_suburb_options($preset){
		// Retrieve a list off all the park suburbs from the database
		$query = 'SELECT DISTINCT suburb FROM parks ORDER BY suburb ASC';
		$result = perform_sql_query($query, null);

		// Exit it there are no results
		if ($result->rowCount() < 1 || is_null($result)){
			exit();
		}

		// Loop through each suburb
		foreach($result as $key => $row){
			// If the suburb is the previously selected suburb the select it
			$append_str = "";
			if ($row['suburb'] == $preset){
				$append_str = " selected";
			}
			
			// echo the suburb option
			echo "<option value=\"".
				$row['suburb'].
				"\"".
				$append_str. //If suburb was previously selected, select it again
				">".
				$row['suburb'].
				"</option>";
		}
	}
?>