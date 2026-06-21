#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *head = free_list_ptr;
  while (head != NULL) {
    if (head->size >= size) {
      return head->id;
    }
    head = head->next;
  }
  printf("No Suitable block found");
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  int best_fit_size = 0;
  struct header *head = free_list_ptr;
  while (head != NULL) {
    if (head->size >= size) {
      if (best_fit_id == -1) {
        best_fit_id = head->id;
        best_fit_size = head->size;
      } else if (head->size < best_fit_size) {
        best_fit_id = head->id;
        best_fit_size = head->size;
      }
    }
    head = head->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  int worst_fit_size = 0;
  struct header *head = free_list_ptr;
  while (head != NULL) {
    if (head->size >= size) {
      if (worst_fit_id == -1) {
        worst_fit_id = head->id;
        worst_fit_size = head->size;
      } else if (head->size > worst_fit_size) {
        worst_fit_id = head->id;
        worst_fit_size = head->size;
      }
    }
    head = head->next;
  }

  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("First Fit ID: %d\n", first_fit_id);
  printf("Best fit ID: %d\n", best_fit_id);
  printf("Worst fit ID %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}

// PART 2
// target_address = head
// while(free_list) {
// if target_address = address of head->next + head->next->size
//   head->size = head->size + head->next->size
//   head->next = head->next->next
//   break
//
// head = head->next
// }
// if head = NULL
//  No free space found
//
//
