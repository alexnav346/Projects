<?php
    chdir(__DIR__);
    require_once('../model/database.php');

    //foreach ($_POST as $in)
    //{
        //echo $in . '<br>';

    //}

    $prodCode = filter_input(INPUT_POST, 'product_id', FILTER_VALIDATE_REGEXP, array("options"=>array("regexp"=>"([A-Z]+\d+)")));

    //echo $prodCode . '<br>';

    if ($prodCode != false)
    {
        $deleteQuery = 'DELETE FROM products WHERE productCode = :code';
        $deleteStatement = $db->prepare($deleteQuery);

        $deleteStatement->bindValue(':code', $prodCode);
        $response = $deleteStatement->execute();

        $deleteStatement->closeCursor();
    }

    include('index.php');
?>