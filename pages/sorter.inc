<?php
/**
 *  labsystem.m-o-p.de - 
 *                  the web based eLearning tool for practical exercises
 *  Copyright (C) 2010  Marc-Oliver Pahl
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
* Displays the sorting form element.
*
* @module     ../pages/sorter.inc
* @author     Marc-Oliver Pahl
* @copyright  Marc-Oliver Pahl 2005
* @version    1.0
*
* @param $_POST['orderBy']  If set this key's value is put into $orderBy.
* @param $_GET['orderBy']   If above one is not set this key's value is put into $orderBy.
* @param $_POST['asc']      If set $asc=$_POST['asc'] else $asc=true.
*
* @return $orderBy          The database key the data should be ordered by.
* @return $asc              Should the order be ascending?
* @return $sorter           The html-code of the sorter.
*/

// The semantics is $orderBy as argument (POST/ GET) is the key used in the $sortArray.
// $orderBy-argument -> $orderByKey (will be used at the {ua}manageUser.php
// $orderBy: The value (DB field) used with the DB-queries.

if ( isset( $_POST['orderBy'] ) ) $orderByKey = $_POST['orderBy'];                      // 1st $_POST['orderBy']
elseif ( !isset( $_GET['orderBy'] ) || 
         !array_key_exists( $orderByKey = stripslashes( $_GET['orderBy'] ), $sortArray ) ) // 2nd $_GET['orderBy']
          $orderByKey = key( $sortArray );                                              // 3rd default (the first el of $sortArray)
  
if ( isset( $_POST['asc'] ) ) $asc = !( $_POST['asc'] == "desc" );
 elseif ( isset( $_GET['asc'] ) )  $asc = !( $_GET['asc'] == "desc" );
 else $asc = true;

// sorting select
$sorter = "<FORM class=\"labsys_mop_sort_form\" NAME=\"sort_options\" METHOD=\"POST\" ACTION=\"".$GLOBALS['url']->link2( $_SERVER['REQUEST_URI'] )."\">\n".
          $lng->get("orderBy").
          '<select name="orderBy" size="1" onChange="document.sort_options.submit();" tabindex="'.$pge->nextTab++.'">';
foreach ( $sortArray as $key => $value ) $sorter .= '<option '.retIfTrue( ( $orderByKey == $key ), " selected" ).'>'.$key.'</option>';
$sorter .='</select> '.
          '<select name="asc" size="1" onChange="document.sort_options.submit();" tabindex="'.$pge->nextTab++.'">
           <option '.retIfTrue(  $asc,  " selected" ).'>asc</option>
           <option '.retIfTrue(  !$asc, " selected" ).'>desc</option>
           </select><input type="submit" value="&gt;&gt;">'.
           "</FORM>\n";
// /sorting select

// below the $orderBy is assumed to be the key for the DB-query
// translate to db fields
  $orderBy = $sortArray[ $orderByKey ]; 
?>