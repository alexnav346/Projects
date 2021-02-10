<?php
    chdir(__DIR__);
    require_once('../model/database.php');

    $prodCodeRaw = filter_input(INPUT_POST, 'prodCode'); 
    $prodName = filter_input(INPUT_POST, 'prodName');
    $prodVer = filter_input(INPUT_POST, 'prodVersion');
    $prodDateRaw = filter_input(INPUT_POST, 'prodDate');

    $prodCodeRaw = trim($prodCodeRaw);
    $prodName = trim($prodName);
    $prodVer = trim($prodVer);
    $prodDateRaw = trim($prodDateRaw);

    $error = "";

    if (empty($prodCodeRaw) || empty($prodName) || empty($prodVer) || empty($prodDateRaw))
    {
        $error = "Error: One or more input fields were empty.<br><br>";
    }
    else
    {
        $prodCode = filter_var($prodCodeRaw, FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"(^[A-Z]+\d+$)")));

        $prodVer = filter_var($prodVer, FILTER_VALIDATE_FLOAT);
    
        $prodDate = filter_var($prodDateRaw, FILTER_VALIDATE_REGEXP,
            array("options"=>array("regexp"=>"/^[\d]{4}-[0-1][0-9]-[0-3][0-9]$/")));
    
    
        if ($prodCode == false)
        {
            $error .= "Error: Product code formatting was incorrect. Format should match [Set of capital letters][Set of numbers]<br><br>";
        }
        if ($prodVer == false)
        {
            $error .= "Error: Product version formatting was incorrect. Version number should have a single decimal point.<br><br>";
        }
        if ($prodDate == false)
        {
            $error .= "Error: Release date format was incorrect. See the format tip on the product adding form.<br><br>";
        }
    }

    if (empty($error))
    {
        $addQuery = 'INSERT INTO products VALUES (:code, :name, :ver, :date)';
        $addQuery = $db->prepare($addQuery);

        $addQuery->bindValue(':code', $prodCode);
        $addQuery->bindValue(':name', $prodName);
        $addQuery->bindValue(':ver', $prodVer);
        $addQuery->bindValue(':date', $prodDate);

        $response = $addQuery->execute();
        $addQuery->closeCursor();

        include('index.php');
    }
    else
    {
        include('../errors/error.php');
    }
?>