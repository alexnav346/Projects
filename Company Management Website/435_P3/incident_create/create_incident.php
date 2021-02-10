<?php
    chdir(__DIR__);
    require_once('../model/database.php');

    $customer = filter_input(INPUT_POST, 'customer'); 
    $product = filter_input(INPUT_POST, 'product');
    $title = filter_input(INPUT_POST, 'title');
    $desc = filter_input(INPUT_POST, 'desc');

    $title = trim($title);
    $desc = trim($desc);

    if (empty($customer) || empty($product) || empty($title) || empty($desc))
    {
        $error = "Error: One or more input fields were empty.<br><br>";
    }

    if (empty($error))
    {
        $addQuery = 'INSERT INTO incidents VALUES (0, :customerID, :prodCode, NULL, NOW(), NULL, :title, :desc)';
        $addQuery = $db->prepare($addQuery);

        $addQuery->bindValue(':customerID', $customer);
        $addQuery->bindValue(':prodCode', $product);
        $addQuery->bindValue(':title', $title);
        $addQuery->bindValue(':desc', $desc);

        $response = $addQuery->execute();
        $addQuery->closeCursor();

        include('success.php');
    }
    else
    {
        include('../errors/error.php');
    }
?>