<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<?php
    $the_last_name = $_POST['lName'];
?>

<main>
    <?php
        $productQuery = 'SELECT * FROM customers WHERE lastName ="' . $the_last_name . '"';
        $queryExec = $db->prepare($productQuery);
        $queryExec->execute();
        $allProducts = $queryExec->fetchAll();

        $queryExec->closeCursor();
    ?>

    <h1>Manage Customers</h1>

    <br>

    <form action="search_customers.php">
        <label for="lName">Last Name:</label>
        <input type="text" id="lName" name="lName">
        <input type="submit" value="Search">
        <br><br>
    </form>

    <table>
        <tr>
            <th>First Name</th>
            <th>Last Name</th>
            <th>Email Address</th>
            <th>Edit</th>
        </tr>
        
        <?php
            foreach ($allProducts as $customer)
            {
                echo 
                    '<tr>' .
                    '<td>' . $customer['firstName'] . '</td>' .
                    '<td>' . $customer['lastName'] . '</td>' .
                    '<td>' . $customer['email'] . '</td>' .
                    '<td>' . 
                        '<form action="select_customer.php" method="post"> ' .
                            '<input type="hidden" name="custID" value="' . $customer['customerID'] . '">' .
                            '<input type="submit" value="Select"> ' .
                        '</form> </td>' .
                    '</tr>';
            }
        ?>
    </table>
    
</main>

<?php include '../view/footer.php'; ?>