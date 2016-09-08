#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

/** @brief  Structure of Manager.
 *  TODO: replace with description of manager
 *  Each theme lists multiple available themes that are within theme directory.
 *  These themes may be used as a selected theme, which may be quickly accessed,
 *  using struct variables. All changes to theme, should be done using available
 *  functions instead of directly manipulating theme. This ensures that all values
 *  are updated correctly.
 */
typedef struct
{
    /** @brief path to currently selected theme.
     *
     *  Selected path points to currently selected theme directory. It may be
     *  accessed quickly using this variable. May be updated using theme_select.
     */
    char *sel_path;

    /** @brief Name of the currently selected theme.
     *
     *  Quick access to name of the currently selected directory. separated from
     *  sel_path since only name is often needed for comparison. May be updated
     *  using theme_select.
     */
    char *sel_name;

    /** @brief path to directory containing all themes.
     *
     *  Path to current root directory, which may contain multiple themes. This
     *  value is required when allocating new theme. Notice that no function to
     *  update this exists since most of the time new theme is created if root
     *  directory is changed.
     */
    char *dir_path;

    /** @brief List of directories within current directory.
     *
     *  Contains all available theme names within this theme's root directory.
     *  These names may be used to changing selected themes etc. May be NULL, in
     *  which case no themes may be changed or selected. THis results always in
     *  NULL value being returned when requesting member variables. May be updated
     *  using theme_update.
     */
    char **dir_list;

    /** @brief Amount of themes in current directory.
     *
     *  Used to track size of the dir_list, because it is not possible to read
     *  it's size direcly. Updated each time theme_update is called.
     */
    int    dir_size;

} Manager;

#endif
