<?php include '../view/header.php'; ?>
<?php require_once '../model/database.php'; ?>

<main>
    <?php
        $techQuery = 'SELECT * FROM technicians';
        $queryExec = $db->prepare($techQuery);
        $queryExec->execute();
        $allTechs = $queryExec->fetchAll();

        $queryExec->closeCursor();
    ?>

    <h1>Technician List</h1>
    <table>
        <tr>
            <th>First Name</th>
            <th>Last Name</th>
            <th>Email</th>
            <th>Phone</th>
            <th>Password</th>
            <th>Options</th>
        </tr>
        
        <?php
            foreach ($allTechs as $tech)
            {
                echo 
                    '<tr>' .
                    '<td>' . $tech['firstName'] . '</td>' .
                    '<td>' . $tech['lastName'] . '</td>' . 
                    '<td>' . $tech['email'] . '</td>' . 
                    '<td>' . $tech['phone'] . '</td>' .
                    '<td>' . $tech['password'] . '</td>' .
                    '<td>' . 
                        '<form action="delete_tech.php" method="post"> ' .
                            '<input type="hidden" name="tech_id" value="' . $tech['techID'] . '">' .
                            '<input type="submit" value="Delete"> ' .
                        '</form> </td>' .
                    '</tr>';
            }
        ?>
    </table>

    <br><a href='add_tech_form.php'>Add Technician</a>
    
</main>

<?php include '../view/footer.php'; ?>