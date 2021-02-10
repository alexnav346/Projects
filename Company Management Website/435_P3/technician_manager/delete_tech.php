<?php
    chdir(__DIR__);
    require_once('../model/database.php');

    $techID = filter_input(INPUT_POST, 'tech_id', FILTER_VALIDATE_INT);

    if ($techID != false)
    {
        $deleteQuery = 'DELETE FROM technicians WHERE techID = :tid';
        $deleteStatement = $db->prepare($deleteQuery);

        $deleteStatement->bindValue(':tid', $techID);
        $response = $deleteStatement->execute();

        $deleteStatement->closeCursor();
    }

    include('index.php');
?>