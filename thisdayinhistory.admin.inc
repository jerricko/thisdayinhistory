<?php
// $Id$
/**
 * @file
 * Module Admin Functions
 *
 * All of the code and functions associated with admin/settings/thisdayinhistory
 */


/**
 * Admin settings screen
 */
function thisdayinhistory_admin_overview() {
  $total = db_result(db_query("SELECT COUNT(*) FROM {node} n where type = 'thisdayinhistory'"));
  return "<label><strong>Content</strong></label>\n<div>Historical events: $total </div>";
}


/**
 * Displays a list of currently-defined blocks.
 */
function thisdayinhistory_blocks_configure() {
  $form = array();
  $form['name'] = array(
    '#type' => 'textfield',
    '#size' => 32,
    '#maxlength' => 64
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add block')
  );

  return $form;
}


/**
 * Renders the block list, including the "Add block" row.
 */
function theme_thisdayinhistory_blocks_configure($form) {
  $header = array(t('Name'), t('Block ID'), t('Filters'), array('data' => t('Operations'), 'colspan' => 2));
  $result = db_query('SELECT tdihb.* FROM {thisdayinhistory_blocks} tdihb ORDER BY tdihb.name');
  $rows = array();

  while ($block = db_fetch_object($result)) {
    $filters = array();

    if ($block->nid_filter) {
      $filters[] = t('node');
    }

    if ($block->rid_filter) {
      $filters[] = t('role');
    }

    if ($block->uid_filter) {
      $filters[] = t('user');
    }

    if ($block->tid_filter) {
      $filters[] = t('term');
    }

    $rows[] = array(
      $block->name,
      $block->bid,
      implode(', ', (count($filters) ? $filters : array(t('none')))),
      l(t('configure block'), "admin/build/block/configure/thisdayinhistory/$block->bid"),
      l(t('delete block'), "admin/settings/thisdayinhistory/blocks/delete/$block->bid")
    );
  }

  $rows[] = array(
    drupal_render($form['name']),
    array('data' => drupal_render($form['submit']), 'colspan' => 4)
  );

  $output = drupal_render($form);

  if (count($rows)) {
    $output .= theme('table', $header, $rows);
  }
  else {
    $output .= theme('table', $header, array(array(array('data' => t('No blocks are defined.'), 'colspan' => 4))));
  }

  return $output;
}


/**
 * Validates that the new block name is valid.
 */
function thisdayinhistory_blocks_configure_validate($form, &$form_state) {
  $name = trim($form_state['values']['name']);

  if (!$name) {
    form_set_error('name', t('You must specify a valid block name.'));
  }
  else if (db_result(db_query("SELECT COUNT(*) FROM {thisdayinhistory_blocks} tdihb WHERE tdihb.name = '%s'", $name))) {
    form_set_error('name', t('The block name %name already exists. Please choose another block name.', array('%name' => $name)));
  }
}


/**
 * Creates the new block.
 */
function thisdayinhistory_blocks_configure_submit($form, &$form_state) {
  db_query("INSERT INTO {thisdayinhistory_blocks}
    (name, block_type, nid_filter, rid_filter, uid_filter, tid_filter, vid, header, header_format)
    VALUES ('%s', 0, '', '', '', '', 0, '', 0)", trim($form_state['values']['name']));
}


/**
 * Confirms the deletion a block.
 */
function thisdayinhistory_block_delete_confirmation($form_state, $bid) {
  $block = db_fetch_object(db_query('SELECT tdihb.name FROM {thisdayinhistory_blocks} tdihb WHERE tdihb.bid = %d', $bid));

  $form = array();
  $form['bid'] = array(
    '#type' => 'value',
    '#value' => $bid
  );
  $form['block_name'] = array(
    '#type' => 'value',
    '#value' => $block->name
  );

  return confirm_form($form, t('Are you sure you want to delete the block %name?', array('%name' => $block->name)), 'admin/settings/thisdayinhistory/blocks', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

/**
 * Deletes the specified block.
 */
function thisdayinhistory_block_delete_confirmation_submit($form, &$form_state) {
  db_query("DELETE FROM {thisdayinhistory_blocks} WHERE bid = %d", $form_state['values']['bid']);
  drupal_set_message(t('The block %name has been removed.', array('%name' => $form_state['values']['block_name'])));
  cache_clear_all();

  $form_state['redirect'] = 'admin/settings/thisdayinhistory/blocks';
  return;
}
