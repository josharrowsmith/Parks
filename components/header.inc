<!DOCTYPE html>
<html>
<head>




		<ul>
	  <li><a href="index.php">HOME</a></li>
	  <li><a href="search.php">SEARCH</a></li>
	  <?php

		//login stuff
		include 'db.php';
	  if(isset($_SESSION) && isset($_SESSION['logged_in'])) {
	      echo '<li><a href="profile.php">PROFILE</a></li>';
	      echo '<li style="float:right"><a href="logout.php">LOGOUT</a></li>';
	      echo '<li style="float:right"><a href="profile.php">'.$user['email'].'</a></li>';

	  }
	  else {
	      echo '<li><a href="signup.php">SIGN UP</a></li>';
	      echo '<li style="float:right"><a href="login.php">LOGIN</a></li>';
	  }
	  ?>
	  </ul>
	</div>

	</html>
