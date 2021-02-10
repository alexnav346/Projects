<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<?php
    $toSearch = $_POST['custID'];
?>

<main>

    <?php
        $productQuery = 'SELECT * FROM customers WHERE customerID ="' . $toSearch . '"';
        $queryExec = $db->prepare($productQuery);
        $queryExec->execute();
        $theCustomer = $queryExec->fetch();
        $queryExec->closeCursor();
    ?>

    <div>

        <h1>Customer Information</h1>

        <br>

        <form action="update_customer.php" method="post">

            <label for='theCustomerID'>Customer ID:</label>
            <input type="text" name='theCustomerID' value="<?php echo $toSearch ?>" readonly> <br><br>

            <label for='fName'>First Name:&nbsp;&nbsp;</label>
            <input type='text' name='fName' value="<?php echo $theCustomer['firstName'] ?>"> <br><br>

            <label for='lName'>Last Name:&nbsp;&nbsp;</label>
            <input type='text' name='lName' value="<?php echo $theCustomer['lastName'] ?>"> <br><br>

            <label for='address'>Address:&nbsp;&nbsp;</label>
            <input type='text' name='address' value="<?php echo $theCustomer['address'] ?>"> <br><br>

            <label for='city'>City:&nbsp;&nbsp;</label>
            <input type='text' name='city' value="<?php echo $theCustomer['city'] ?>"> <br><br>

            <label for="state">State:&nbsp;&nbsp;</label>
            <input type='text' name ='state' value="<?php echo $theCustomer['state'] ?>"> <br><br>

            <label for="postalCode">Postal Code:&nbsp;&nbsp;</label>
            <input type='text' name ='postalCode' value="<?php echo $theCustomer['postalCode'] ?>"> <br><br>

            <label for="countryCode">Country Code:&nbsp;&nbsp;</label>
            <input type='text' name ='countryCode' value="<?php echo $theCustomer['countryCode'] ?>"> <br><br>

            <label for="phone">Phone:&nbsp;&nbsp;</label>
            <input type='text' name ='phone' value="<?php echo $theCustomer['phone'] ?>"> <br><br>

            <label for="email">Email:&nbsp;&nbsp;</label>
            <input type='text' name ='email' value="<?php echo $theCustomer['email'] ?>"> <br><br>

            <label for="password">Password:&nbsp;&nbsp;</label>
            <input type='text' name ='password' value="<?php echo $theCustomer['password'] ?>"><br><br>

            <input type='submit'value='Update Customer'>
            
        </form>

    </div>

</main>


<?php include '../view/footer.php'; ?>