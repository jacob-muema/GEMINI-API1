# Defines the variables for the episode

variable "name" {
  type        = string
  description = "The name of the bucket to be created"
}

variable "region" {
  type        = string
  description = "The AWS region where the bucket needs to be created"
}

variable "project" {
  type        = string
  description = "The Project to deploy the bucket"
}

variable "tags" {
  type        = map(string)
  description = "The Tags to be applied to the buket"
  default     = {}
}
