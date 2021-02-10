<?php require_once '../model/database.php'; ?>

<?php
    $customerID = $_POST['theCustomerID'];
    $firstName = $_POST['fName'];
    $lastName = $_POST['lName'];
    $theAddress = $_POST['address'];
    $city = $_POST['city'];
    $state = $_POST['state'];
    $postalCode = $_POST['postalCode'];
    $countryCode = $_POST['countryCode'];
    $phone = $_POST['phone'];
    $email = $_POST['email'];
    $password = $_POST['password'];
?>

<main>
        <?php

            $updateQuery = 'UPDATE customers
                            SET customerID = :theID, firstName = :firstName, lastName = :lastName, address = :theAddress, city = :city, 
                            state =:theState, postalCode = :postalCode, countryCode = :countryCode, phone = :phone,
                            email = :email, password = :thePass
                            WHERE customerID = :theID';

            $updateQuery = $db->prepare($updateQuery);

            $updateQuery->bindValue(':theID', $customerID);
            $updateQuery->bindValue(':firstName', $firstName);
            $updateQuery->bindValue(':lastName', $lastName);
            $updateQuery->bindValue(':theAddress', $theAddress);
            $updateQuery->bindValue(':city', $city);
            $updateQuery->bindValue(':theState', $state);
            $updateQuery->bindValue(':postalCode', $postalCode);
            $updateQuery->bindValue(':countryCode', $countryCode);
            $updateQuery->bindValue(':phone', $phone);
            $updateQuery->bindValue(':email', $email);
            $updateQuery->bindValue(':thePass', $password);

            $response = $updateQuery->execute();
            $updateQuery->closeCursor();

            include('index.php');
        ?>
</main>