<?php
// $Id: thisdayinhistory-block-content.tpl.php,v 1.1 2009/02/10 19:40:01 dmcgladdery Exp $
/**
 * @file
 * Default template for TDiH block content
 */

  foreach ($node_list as $node) {
    $nodes_by_year[$node->year][] = $node;
  }

  foreach ($nodes_by_year as $year => $year_list) {
    foreach ($year_list as $node) {
      $n = node_view($node,'teaser');
      $body = field_get_items('node', $node, 'body');
      $row = array(
        array('data' => '<p>'. $node->year .':</p>', 'valign' => 'top', 'class' => 'year-column'),
        array('data' => text_summary($body[0]['value'])),
      );
      $tablerows[] = $row;
    }
  }

  $attributes = array('class' => 'tdih-events');
  print $block['header'] . theme('table', array('header' => array(), 'rows' => $tablerows, 'attributes' => $attributes));
