# Create a GCS bucket

resource "google_storage_bucket" "buckets" {
  for_each = { for bucket in var.bucket_list : bucket.name => bucket }
  name     = each.key
  project  = var.project
  location = each.value.region
  labels   = each.value.tags
}
