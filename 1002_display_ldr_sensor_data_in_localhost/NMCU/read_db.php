<!DOCTYPE html>
<html>
	<head>
		<style>
			table {
				border-collapse: collapse;
				width: 100%;
				color: #1f5380;
				font-family: monospace;
				font-size: 20px;
				text-align: left;
			} 
			th {
				background-color: #1f5380;
				color: white;
			}
			tr:nth-child(even) {background-color: #f2f2f2}
		</style>
	</head>
	<?php
		//Creates new record as per request
		//Connect to database
		$hostname = "localhost";
		$username = "root";
		$password = "";
		$dbname = "ldr_esp";
		// Create connection
		$conn = mysqli_connect($hostname, $username, $password, $dbname);
		// Check connection
		if (!$conn) {
			die("Connection failed !!!");
		} 
	?>
	<body>
		<!-- TO export data to a file -->
		
		<form method="post" action="export.php">
			<input type="submit" name="export" value="CSV Report">
		</form>	

		<center><table style ="width:700px;"></center>
			<tr>
				<th>ID</th>
				<th>Sensor Value</th>
				<th>Date</th>
				<th>Time</th>
			</tr>	
			<?php
				$table = mysqli_query($conn, "SELECT id, status, Date, Time FROM logs");
				while($row = mysqli_fetch_array($table))
				{
			?>
			<tr>
				<td><?php echo $row["id"]; ?></td>
				<td><?php echo $row["status"]; ?></td>
				<td><?php echo $row["Date"]; ?></td>
				<td><?php echo $row["Time"]; ?></td>
			</tr>
			<?php
				}
			?>
		</table>
	</body>
</html>