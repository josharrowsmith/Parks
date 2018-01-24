<!DOCTYPE html>
<html>
<?php
include "php/common.inc";
session_start();
?>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <script type="text/javascript" src="js/javascript.js"></script>

</head>
<body>
<?php include 'components/header.inc';?>
<div id="body">
    <p id="title">Error</p>
    <?php display_error_message();?>
</div>
<?php include 'components/footer.inc'; ?>
</body>
</html>
