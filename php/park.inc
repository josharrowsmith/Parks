<?php
	// Function:  get_park_by_id($parkID)
	// Description: a function to get park by its id
	// Input: park id
	// Output: park data
	function get_park_by_id($parkID){
		$query = "SELECT * from parks WHERE parkID = ".$parkID;
		$result = perform_sql_query($query, null);
		return $result;
	}

	// Function:  get_previews_by_id($parkID)
	// Description: a function to get reviews for park by its id
	// Input: park id
	// Output: park review data
	function get_reviews_by_id($parkID){
		$query = 'SELECT * FROM reviews '.
			'WHERE parkID=:parkID '.
			'ORDER BY dateCreated DESC';
		$parameters['parkID'] = htmlspecialchars($parkID, ENT_QUOTES, 'UTF-8');

		$result = perform_sql_query($query, $parameters);

		if ($result->rowCount() > 0){
			return $result;
		}

	}


	// Function:  display_reviews($review_data)
	// Description: a function to display the parks reviews
	// Input: the parks review data
	// Output: none
	function display_reviews($review_data){

		// if there are no reviews
		if(is_null($review_data)){
			// the print a message
			echo '<p class="error">There are no reviews for this park</p>';
		} else {
			// Loop through each review
			foreach($review_data as $review){
				// Change date into an acceptable format
				$dateText = date("d M Y", strtotime($review['dateCreated']));
				$datePublished = date("y-m-d", strtotime($review['dateCreated']));

				// Echo out the review including mirco-data and meta-data
				echo 	"<div itemprop='review' itemscope itemtype='http://schema.org/Review'>
							<p>
								<b><span id='reviewRating' itemprop='reviewRating' itemscope itemtype='http://schema.org/Rating'>
									<span itemprop='ratingValue'>".$review['rating']."</span> out of
									<span itemprop='bestRating'>5</span> stars
								</span></b> -
								\"<i><span itemprop='name'>".$review['message']."</span></i>\" -
								<b><span itemprop='author'>".$review['username']."</span></b>
								on ".$dateText."<br>
								<meta itemprop='datePublished' content=".$datePublished.">
							</p>
						</div>";
			}
		}
	}

	// Function:  add_review(array $data)
	// Description: a function to add a review to the database
	// Input: the new review data
	// Output: none
	function add_review(array $data){
		// remove and cross site scripting
		$username = $_SESSION['username'];
		$parkID = htmlspecialchars($data['parkID'], ENT_QUOTES, 'UTF-8');
		$message = htmlspecialchars($data['message'], ENT_QUOTES, 'UTF-8');
		$rating = htmlspecialchars($data['rating'], ENT_QUOTES, 'UTF-8');
		$category = htmlspecialchars($data['category'], ENT_QUOTES, 'UTF-8');

		// If the user has already created a review
		if(is_previous_review($parkID, $username)){
			// Update previous review
			update_previous_review($parkID, $username, $message, $rating, $category);
			$_SESSION['errorMessage'] = 'You have already reviewed this park<br>'.
				'Your previous review has been updated';

		}else{
			// Otherwise create a new review
			create_new_review($parkID, $username, $message, $rating, $category);
		}

		// Finally update the parks info based on the new values of the review
		update_park_info($parkID);
	}




	// Function:  create_new_review($parkID, $username, $message, $rating, $category)
	// Description: a function to create a new review
	// Input: the parkID, username, message, rating and category
	// Output: none
	function create_new_review($parkID, $username, $message, $rating, $category){
		$query = ''.
			'INSERT INTO reviews (parkID, username, message, rating, category) '.
			'VALUES(:parkID, :username, :message, :rating, :category)';

		$parameters['parkID'] = intval($parkID);
		$parameters['username'] = $username;
		$parameters['message'] = $message;
		$parameters['rating'] = intval($rating);
		$parameters['category'] = $category;

		$result = perform_sql_query($query, $parameters);
	}


?>
