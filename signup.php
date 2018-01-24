<?php


include 'db.php';

if( isset($_SESSION['user_id']) ){
	header("Location: /");
}


$message = '';

$records = $pdo->prepare('SELECT email FROM users WHERE email = :email');
$records->bindParam(':email', $_POST['email']);
$records->execute();

if ( $records->rowcount() > 0 ) {

	echo "<script>
	alert('User already exist');
	window.location.href='signup.php';
	</script>";
}




elseif(!empty($_POST['email']) && !empty($_POST['password'])){

	// Enter the new user in the database
	$sql = "INSERT INTO users (email, password, firstname) VALUES (:email, :password,:firstname)";
	$stmt = $pdo->prepare($sql);

	$stmt->bindParam(':email', $_POST['email']);
	$stmt->bindParam(':password', password_hash($_POST['password'], PASSWORD_BCRYPT));
	$stmt->bindParam(':firstname', $_POST['firstname']);




	if( $stmt->execute() ){

		echo "<script>
		alert('It worked, Please login');
		window.location.href='index.php';
		</script>";
	}
	else{
		$message = 'Sorry there must have been an issue creating your account';
		}

	}


?>


<head>
  <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Park</title>
      <link rel="stylesheet" type="text/css" href="css/style.css">
      </head>
      <body>
        <?php include 'components/header.inc';
        include "php/common.inc";
        include "php/results.inc"; ?>

        <div id="body">
        <br>
        <p id="title">Sign Up</p>

        <form action="signup.php" method="POST">


        <input type="email" placeholder="Enter your email" name="email" required placeholder="Enter a valid email address">
        <input type="password" placeholder="and password" name="password">
        <input type="password" placeholder="confirm password" name="confirm_password">
        <input type='text' name='firstname' id='firstname' placeholder='First Name' value='' required/>

        <input type="submit" class="submit" id="search_btn" value="signup">
      </div>
        </form>
        <?php include 'components/footer.inc'; ?>

</body>
</html>
