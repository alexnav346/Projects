<?php
    chdir(__DIR__);
    require_once('../model/database.php');

    $fNameRaw = filter_input(INPUT_POST, 'fName'); 
    $lNameRaw = filter_input(INPUT_POST, 'lName');
    $emailRaw = filter_input(INPUT_POST, 'email');
    $phoneRaw = filter_input(INPUT_POST, 'phone');
    $passRaw = filter_input(INPUT_POST, 'password');

    $fName = trim($fNameRaw);
    $lName = trim($lNameRaw);
    $email = trim($emailRaw);
    $phone = trim($phoneRaw);
    $pass = trim($passRaw);

    $error = "";

    if (empty($fName) || empty($lName) || empty($email) || empty($phone) || empty($pass))
    {
        $error .= "Error: One or more input fields were empty.<br><br>";
    }
    else
    {
        $fName = filter_var($fName, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"(^[A-Za-z\-']+$)")));
        $lName = filter_var($lName, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"(^[A-Za-z\-']+$)")));

        $email = filter_var($email, FILTER_VALIDATE_EMAIL);
    
        $phone = filter_var($phone, FILTER_VALIDATE_REGEXP,
            array("options"=>array("regexp"=>"/^[\d]{3}-[\d]{3}-[\d]{4}$/")));

        $passHasWhitespace = filter_var($pass, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"(^.* .*$)")));
    
        if ($fName == false || $lName == false)
        {
            $error .= "Error: Technician names may contain only letters, hyphens, and apostrophes.<br><br>";
        }
        if ($email == false)
        {
            $error .= "Error: Email address was invalid<br><br>";
        }
        if ($phone == false)
        {
            $error .= "Error: Phone number format was incorrect. See the format tip on the technician form.<br><br>";
        }
        if ($passHasWhitespace != false)
        {
            $error .= "Error: Password cannot contain spaces.<br><br>";
        }
    }

    if (empty($error))
    {
        $addQuery = "INSERT INTO technicians VALUES (0, :fname, :lname, :email, :phone, :pass)";
        $addQuery = $db->prepare($addQuery);

        $addQuery->bindValue(':fname', $fName);
        $addQuery->bindValue(':lname', $lName);
        $addQuery->bindValue(':email', $email);
        $addQuery->bindValue(':phone', $phone);
        $addQuery->bindValue(':pass', $pass);

        $response = $addQuery->execute();
        $addQuery->closeCursor();

        include('index.php');
    }
    else
    {
        include('../errors/error.php');
    }
?>