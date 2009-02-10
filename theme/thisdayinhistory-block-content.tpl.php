<?php
// $Id$
/**
 * @file
 * Default template for TDiH block content
 */

  drupal_add_css(drupal_get_path('module', 'thisdayinhistory') .'/thisdayinhistory.css');

  foreach ($node_list as $node) {
    $nodes_by_year[$node->year][] = $node;
  }

  foreach ($nodes_by_year as $year => $year_list) {
    foreach ($year_list as $node) {
      $row = array(
        array('data' => '<p>'. $node->year .':</p>', 'valign' => 'top', 'class' => 'year-column'),
        array('data' => $node->teaser),
      );
      $tablerows[] = $row;
    }
  }

  $attributes = array('class' => 'tdih-events');
  print $block['header'] . theme('table', array(), $tablerows, $attributes);
