# Values for the variables

subscription_id = "" # Update with your ID
rg_name         = "rg-dl-tf-ep14"
local_bkt_name  = "dl-yt-ep14"

storage_accounts = [
  {
    name           = "dl-yt-ep14-loop1"
    location       = "eastasia"
    container_list = ["images", "videos", "pdfs"]
  },
  {
    name           = "dl-yt-ep14-loop2"
    location       = "eastus"
    container_list = ["diagrams", "codes"]
  }
]
