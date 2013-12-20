/*
 * fasp_wirepath_ruleset.h
 *
 * List of actions that need to be taken in receiver-side path handling.
 *
 * Aspera, Inc.
 *
 */

/*                                                            multiple_sources
                                                              |dest_is_dir
                                                              ||dest_exists
                                                              |||dest_parent_exists
                                                              ||||source_is_dir
                                                              |||||create_dir 
                                                              |||||| */
e_wp_fail_destination_does_not_exist,                      /* 000000 */
e_wp_create_destination_dir_and_place_under,               /* 000001 */ //e_wp_place_under_destination_dir
e_wp_fail_destination_does_not_exist,                      /* 000010 */ //e_wp_fail_destination_parent_does_not_exist
e_wp_create_destination_dir_and_place_under,               /* 000011 */ //e_wp_fail_destination_is_file,
e_wp_replace_destination_file,                             /* 000100 */ // *** these two lines are
e_wp_create_destination_dir_and_place_under,               /* 000101 */ // *** suspicious but correct according to the spec
e_wp_create_destination_dir_and_place_contents_under,      /* 000110 */ //e_wp_fail_destination_does_not_exist,
e_wp_create_destination_dir_and_place_under,               /* 000111 */ //e_wp_fail_destination_is_file,
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 001000 */ //e_wp_replace_destination_file
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 001001 */ //e_wp_replace_destination_file
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 001010 */ //e_wp_fail_destination_parent_does_not_exist
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 001011 */ //e_wp_fail_destination_is_file
e_wp_replace_destination_file,                             /* 001100 */
e_wp_fail_destination_is_file,                             /* 001101 */ //e_wp_replace_destination_file
e_wp_fail_destination_is_file,                             /* 001110 */
e_wp_fail_destination_is_file,                             /* 001111 */
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 010000 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 010001 */ //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 010010 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 010011 */ //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 010100 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 010101 */ //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 010110 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 010111 */ //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 011000 */ //e_wp_place_under_destination_dir
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 011001 */ //e_wp_place_under_destination_dir
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 011010 */
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 011011 */
e_wp_place_under_destination_dir,                          /* 011100 */
e_wp_place_under_destination_dir,                          /* 011101 */
e_wp_place_under_destination_dir,               /* 30 */   /* 011110 */
e_wp_place_under_destination_dir,                          /* 011111 */
/*                                                            multiple_sources
                                                              |dest_is_dir
                                                              ||dest_exists
                                                              |||dest_parent_exists
                                                              ||||source_is_dir
                                                              |||||create_dir 
                                                              |||||| */
e_wp_fail_destination_does_not_exist,           /* 32 */   /* 100000 */
e_wp_create_destination_dir_and_place_under,               /* 100001 */ //e_wp_place_under_destination_dir
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 100010 */ //e_wp_fail_destination_is_file,
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 100011 */ //e_wp_fail_destination_is_file,
e_wp_fail_destination_does_not_exist,                      /* 100100 */ //e_wp_replace_destination_file
e_wp_create_destination_dir_and_place_under,               /* 100101 */
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 100110 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 100111 */ //e_wp_fail_destination_is_file, //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 101000 */ //e_wp_replace_destination_file
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 101001 */ //e_wp_replace_destination_file
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 101010 */ //e_wp_fail_destination_parent_does_not_exist
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 101011 */ //e_wp_fail_destination_is_file
e_wp_fail_destination_is_file,                             /* 101100 */ //e_wp_replace_destination_file
e_wp_fail_destination_is_file,                             /* 101101 */ //e_wp_replace_destination_file
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 101110 */ //e_wp_fail_destination_is_file
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 101111 */ //e_wp_fail_destination_is_file
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 110000 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 110001 */ //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 110010 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 110011 */ //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 110100 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // dest is dir and doesn't exist  /* 110101 */ //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 110110 */ //e_wp_fail_destination_does_not_exist
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 110111 */ //e_wp_create_destination_dir_and_place_under
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 111000 */ //e_wp_place_under_destination_dir
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 111001 */ //e_wp_place_under_destination_dir
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 111010 */
e_wp_fail_invalid_facts, // dest exists, parent doesn't    /* 111011 */
e_wp_place_under_destination_dir,               /* 60 */   /* 111100 */
e_wp_place_under_destination_dir,                          /* 111101 */
e_wp_fail_invalid_facts, // sourceIsDir, multipleSources   /* 111110 */ //e_wp_place_under_destination_dir
e_wp_fail_invalid_facts  // sourceIsDir, multipleSources   /* 111111 */ //e_wp_place_under_destination_dir
