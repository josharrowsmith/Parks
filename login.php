<?php



include 'db.php';


if( isset($_SESSION['user_id']) ){
	//checking if login
}


if(!empty($_POST['email']) && !empty($_POST['password'])):

	$records = $pdo->prepare('SELECT id,email,password FROM users WHERE email = :email');
	$records->bindParam(':email', $_POST['email']);
	$records->execute();
	$results = $records->fetch(PDO::FETCH_ASSOC);

	$message = '';
	//checking if password match
	if(count($results) > 0 && password_verify($_POST['password'], $results['password']) ){

		$_SESSION['user_id'] = $results['id'];
		$_SESSION['logged_in'] = true;
		$_SESSION['email'] = $email;

		header("Location: index.php");

	} else {
		$message = 'Sorry, those credentials do not match';
	}

endif;

?>

<head>
  <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Park</title>
      <link rel="stylesheet" type="text/css" href="css/style.css">
      </head>
      <body>
        <?php include 'components/header.inc'; ?>

        <div id="body">
        <br>
        <p id="title">Sign In</p>


        <form action="login.php" method="POST">

        <input type="text" placeholder="Enter your email" name="email">
        <input type="password" placeholder="and password" name="password">

        <input type='submit' class='submit' name='login' value='Sign In'/>
        </div>
        </form>


        <?php include 'components/footer.inc'; ?>

</body>
</html>
