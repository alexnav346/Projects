<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<?php
    //Input validation
    $emailRaw = filter_input(INPUT_POST, 'email');
    $email = trim($emailRaw);

    if (empty($email))
    {
        $error = "Error: No email address entered.";
    }
    else
    {
        $email = filter_var($email, FILTER_VALIDATE_EMAIL);

        if ($email == false)
        {
            $error = "Error: Invalid email address supplied.";
        }
        else
        {
            //If the email is good, get the customer details
            $customerQuery = "SELECT customerID, firstName, lastName 
                         FROM customers 
                         WHERE email = :inputEmail";

            $customerQuery = $db->prepare($customerQuery);
            $customerQuery->bindValue(':inputEmail', $email);

            $response = $customerQuery->execute();
            $customerInfo = $customerQuery->fetch();

            $customerQuery->closeCursor();

            if (empty($customerInfo))
            {
                $error = "Error: No customer match found for " . $emailRaw . ".";
            }
        }
    }

    //Verify that the selected user actually has products registered
    if (empty($error))
    {
        $registeredQuery = "SELECT productCode 
                            FROM registrations 
                            WHERE customerID = :cid";

        $registeredQuery = $db->prepare($registeredQuery);
        $registeredQuery->bindValue(':cid', $customerInfo['customerID']);

        $response = $registeredQuery->execute();
        $registeredProducts = $registeredQuery->fetchAll();

        $registeredQuery->closeCursor();

        if (empty($registeredProducts))
        {
            $error = 'Error: ' . $customerInfo['firstName'] . " " . $customerInfo['lastName'] . 
                    ' has no products registered to them.';
        }
    }

    //Get the names of the products for the selection box
    if (empty($error))
    {
        $productQuery = "SELECT name 
                        FROM products 
                        WHERE productCode IN (";

        foreach ($registeredProducts as $product)
        {
            $productQuery .= '"' . $product['productCode'] . '",';
        }
        //Replace the trailing comma with the closing parentheses
        $productQuery[strlen($productQuery) - 1] = ')';

        $productQuery = $db->prepare($productQuery);
        $productQuery->bindValue(':cid', $customerInfo['customerID']);

        $response = $productQuery->execute();
        $productNames = $productQuery->fetchAll();

        $productQuery->closeCursor();
    }

    //Serve error page
    if (empty($error) == false) :
        include('../errors/error.php');
    else :
?>

<main>
    <h1>Create Incident</h1>

    <form action="create_incident.php" method="post">
        <p>Customer: <?php echo $customerInfo['firstName'] . " " . $customerInfo['lastName'];?></p>
        <input type='hidden' name="customer" value='<?php echo $customerInfo['customerID'];?>'><br>

        <label for="product">Product:</label>
        <select name="product">
            <?php
                for ($i = 0; $i < count($productNames); $i++)
                {
                    echo '<option value="' . $registeredProducts[$i]['productCode'] . '">';
                    echo $productNames[$i]['name'] . '</option>';
                }
            ?>
        </select><br><br>

        <label for="title">Title:</label>
        <input type='text' name="title"><br><br>

        <label for="desc">Description:</label>
        <textarea name="desc" rows="3" cols="40"></textarea><br><br>

        <input type="submit" value="Create Incident">
    </form>
</main>

<?php include '../view/footer.php'; ?>
<?php endif?>
