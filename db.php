<?php
$dsn = "mysql:host=localhost;dbname=test";
$db_user = 'admin';
$db_password = 'secret';
try {
  $pdo = new PDO($dsn, $db_user, $db_password);
  $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  // echo "you connected successfully";
} catch(PDOException $e){
  die('connection fails'.$e -> getMessage());
}

// session_start();

    if(!isset($_SESSION))
    {
        session_start();
    }


	if( isset($_SESSION['user_id']) ){
        $records = $pdo->prepare('SELECT id,email,password FROM users WHERE id = :id');
        $records->bindParam(':id', $_SESSION['user_id']);
        $records->execute();
        $results = $records->fetch(PDO::FETCH_ASSOC);

        $user = NULL;

        if( count($results) > 0){
        $user = $results;
        }
        else{
            $user = "nop";
    }

	}

?>
