<html>
<head>
   <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
   <meta name="Author" content="Jonny Fillmore">
   <title>ACM Member List</title>
   <link href="php.css" rel="stylesheet" type="text/css">
</head>  	
<body>
<?php
$dbconn = pg_Connect ("dbname=acm user=acm password=nan0gram");
if ($dbconn == FALSE)
	die("<h2>Database unavailable.  Try again later.</h2>");

?>
<div id="indent">
<table width="95%" border="0" cellspacing="0" cellpadding="0">
    <tr align="left" valign="top"> 
      <td width="223"> 
        <table width="200" border="0" cellspacing="0" cellpadding="0" align="center">
          <tr> 
            <td class="BoxHeader">Club Information</td>
          </tr>
          <tr> 
            <td class="BoxItem"><a href="http://www.cs.usu.edu/~acm/club_information/club_organization.htm">Club Organization</a></td>
          </tr>
          <tr> 
            <td class="BoxItem"><a href="http://otherland.cs.usu.edu/~acm/member_list.php">Member 
              List</a></td>
          </tr>
          <tr> 
            <td class="BoxItem"><a href="http://www.cs.usu.edu/~acm/club_information/additional_information.htm">Additional 
              Information</a></td>
          </tr>
          <tr> 
            <td class="BoxItem"><a href="http://otherland.cs.usu.edu/~acm/interest_survey_results.php">Interest 
              Survey Results</a></td>
          </tr>
          <tr> 
            <td class="BoxItem"><a href="http://otherland.cs.usu.edu/~acm/joining_acm.php">Joining 
              ACM</a></td>
          </tr>
        </table>
        <br>
      </td>
      <td valign="top">
      
      <table width="100%" cellspacing="1" cellpadding="1" border="0">

  <?php
  $mySQL = "SELECT name, major, yrinschool, pnumber, email FROM members WHERE privacy = 'f' ORDER BY name;";
  $result = pg_exec($dbconn, $mySQL);
  $row = 0;
	$num = pg_numrows($result); 
	while ($row < $num && $data = pg_fetch_object ($result, $row))
	{
	    echo"<tr><td class=\"MemberName\">",$data->name,"</td>
	         <td class=\"MemberDetail\">";
              switch ($data->yrinschool)
	    {
		case 1: echo "Freshman"; break;
		case 2: echo "Sophomore"; break;
		case 3: echo "Junior"; break;
		case 4: echo "Senior"; break;
		case 5: echo "1st Yr Grad. Student"; break;
		case 6: echo "2nd Yr Grad. Student"; break;
	    }
	    echo "</td></tr>
	          <tr><td colspan=\"2\" class=\"MemberDetail\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Major: ",$data->major,"</td></tr>
	          <tr><td colspan=\"2\" class=\"MemberDetail\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Phone Number:",$data->pnumber,"</td></tr>
                  <tr><td colspan=\"2\" class=\"MemberDetail\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;E-Mail: ",$data->email,"</td></tr>
                  <tr><td colspan=\"2\">&nbsp;</td></tr>";		
	    $row++;
	}
?>
</table></td></tr></table>
<br><br>In the future look for the ability to look up members based upon interests 
  and skills, change your record and upload your photograph and link to homepage.
</div></body></html>
